#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct symt {int /*<<< orphan*/  tag; } ;
struct TYPE_6__ {char const* name; } ;
struct symt_udt {struct symt symt; TYPE_1__ hash_elt; } ;
struct symt_enum {int dummy; } ;
struct ParseTypedefData {char* ptr; int idx; int /*<<< orphan*/  module; int /*<<< orphan*/  buf; } ;
typedef  enum UdtKind { ____Placeholder_UdtKind } UdtKind ;
struct TYPE_10__ {struct symt symt; } ;
struct TYPE_9__ {struct symt symt; } ;
struct TYPE_8__ {struct symt symt; } ;
struct TYPE_7__ {struct symt symt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  PTS_ABORTIF (struct ParseTypedefData*,int) ; 
 int /*<<< orphan*/  SymTagUDT ; 
 int /*<<< orphan*/  TRACE (char*,long,long,int /*<<< orphan*/ ) ; 
 int UdtStruct ; 
 int UdtUnion ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btVoid ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 struct symt** stabs_find_ref (long,long) ; 
 int stabs_get_basic (struct ParseTypedefData*,int,struct symt**) ; 
 int stabs_pts_read_aggregate (struct ParseTypedefData*,struct symt_udt*) ; 
 int stabs_pts_read_array (struct ParseTypedefData*,struct symt**) ; 
 int stabs_pts_read_enum (struct ParseTypedefData*,struct symt_enum*) ; 
 int stabs_pts_read_id (struct ParseTypedefData*) ; 
 int stabs_pts_read_number (struct ParseTypedefData*,long*) ; 
 int stabs_pts_read_range (struct ParseTypedefData*,char const*,struct symt**) ; 
 int stabs_pts_read_type_reference (struct ParseTypedefData*,long*,long*) ; 
 int strcmp (char const*,char const*) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  symt_get_name (struct symt*) ; 
 TYPE_5__* symt_new_basic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 TYPE_4__* symt_new_enum (int /*<<< orphan*/ ,char const*,struct symt*) ; 
 TYPE_3__* symt_new_function_signature (int /*<<< orphan*/ ,struct symt*,int) ; 
 TYPE_2__* symt_new_pointer (int /*<<< orphan*/ ,struct symt*,int) ; 
 struct symt_udt* symt_new_udt (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stabs_pts_read_type_def(struct ParseTypedefData* ptd, const char* typename,
                                   struct symt** ret_dt)
{
    int			idx;
    long		sz = -1;
    struct symt*	new_dt = NULL;     /* newly created data type */
    struct symt*	ref_dt;		   /* referenced data type (pointer...) */
    long		filenr1, subnr1, tmp;

    /* things are a bit complicated because of the way the typedefs are stored inside
     * the file, because addresses can change when realloc is done, so we must call
     * over and over stabs_find_ref() to keep the correct values around
     */
    PTS_ABORTIF(ptd, stabs_pts_read_type_reference(ptd, &filenr1, &subnr1) == -1);

    while (*ptd->ptr == '=')
    {
	ptd->ptr++;
	PTS_ABORTIF(ptd, new_dt != NULL);

	/* first handle attribute if any */
	switch (*ptd->ptr)      
        {
	case '@':
	    if (*++ptd->ptr == 's')
            {
		ptd->ptr++;
		if (stabs_pts_read_number(ptd, &sz) == -1)
                {
		    ERR("Not an attribute... NIY\n");
		    ptd->ptr -= 2;
		    return -1;
		}
		PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
	    }
	    break;
	}
	/* then the real definitions */
	switch (*ptd->ptr++)
        {
	case '*':
        case '&':
	    PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &ref_dt) == -1);
	    new_dt = &symt_new_pointer(ptd->module, ref_dt, sizeof(void*))->symt;
           break;
        case 'k': /* 'const' modifier */
        case 'B': /* 'volatile' modifier */
            /* just kinda ignore the modifier, I guess -gmt */
            PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, typename, &new_dt) == -1);
	    break;
	case '(':
	    ptd->ptr--;
            PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, typename, &new_dt) == -1);
	    break;
	case 'a':
	    PTS_ABORTIF(ptd, stabs_pts_read_array(ptd, &new_dt) == -1);
	    break;
	case 'r':
	    PTS_ABORTIF(ptd, stabs_pts_read_range(ptd, typename, &new_dt) == -1);
	    assert(!*stabs_find_ref(filenr1, subnr1));
	    *stabs_find_ref(filenr1, subnr1) = new_dt;
	    break;
	case 'f':
	    PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &ref_dt) == -1);
	    new_dt = &symt_new_function_signature(ptd->module, ref_dt, -1)->symt;
	    break;
	case 'e':
            stabs_get_basic(ptd, 1 /* int */, &ref_dt);
            new_dt = &symt_new_enum(ptd->module, typename, ref_dt)->symt;
	    PTS_ABORTIF(ptd, stabs_pts_read_enum(ptd, (struct symt_enum*)new_dt) == -1);
	    break;
	case 's':
	case 'u':
            {
                struct symt_udt*    udt;
                enum UdtKind kind = (ptd->ptr[-1] == 's') ? UdtStruct : UdtUnion;
                /* udt can have been already defined in a forward definition */
                udt = (struct symt_udt*)*stabs_find_ref(filenr1, subnr1);
                if (!udt)
                {
                    udt = symt_new_udt(ptd->module, typename, 0, kind);
                    /* we need to set it here, because a struct can hold a pointer
                     * to itself
                     */
                    new_dt = *stabs_find_ref(filenr1, subnr1) = &udt->symt;
                }
                else
                {
                    unsigned l1, l2;
                    if (udt->symt.tag != SymTagUDT)
                    {
                        ERR("Forward declaration (%p/%s) is not an aggregate (%u)\n",
                            udt, symt_get_name(&udt->symt), udt->symt.tag);
                        return -1;
                    }
                    /* FIXME: we currently don't correctly construct nested C++
                     * classes names. Therefore, we could be here with either:
                     * - typename and udt->hash_elt.name being the same string
                     *   (non embedded case)
                     * - typename being foo::bar while udt->hash_elt.name being 
                     *   just bar
                     * So, we twist the comparison to test both occurrences. When
                     * we have proper C++ types in this file, this twist has to be
                     * removed
                     */
                    l1 = strlen(udt->hash_elt.name);
                    l2 = strlen(typename);
                    if (l1 > l2 || strcmp(udt->hash_elt.name, typename + l2 - l1))
                        ERR("Forward declaration name mismatch %s <> %s\n",
                            udt->hash_elt.name, typename);
                    new_dt = &udt->symt;
                }
                PTS_ABORTIF(ptd, stabs_pts_read_aggregate(ptd, udt) == -1);
	    }
	    break;
	case 'x':
	    idx = ptd->idx;
            tmp = *ptd->ptr++;
	    PTS_ABORTIF(ptd, stabs_pts_read_id(ptd) == -1);
	    switch (tmp)
            {
	    case 'e':
                stabs_get_basic(ptd, 1 /* int */, &ref_dt);
                new_dt = &symt_new_enum(ptd->module, ptd->buf + idx, ref_dt)->symt;
                break;
	    case 's':
                new_dt = &symt_new_udt(ptd->module, ptd->buf + idx, 0, UdtStruct)->symt;
	        break;
            case 'u':
                new_dt = &symt_new_udt(ptd->module, ptd->buf + idx, 0, UdtUnion)->symt;
	        break;
	    default:
                return -1;
	    }
	    ptd->idx = idx;
	    break;
	case '-':
            {
                PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &tmp) == -1);
                PTS_ABORTIF(ptd, stabs_get_basic(ptd, tmp, &new_dt) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
            }
	    break;
        case '#':
            if (*ptd->ptr == '#')
            {
                ptd->ptr++;
                PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &ref_dt) == -1);
                new_dt = &symt_new_function_signature(ptd->module, ref_dt, -1)->symt;
            }
            else
            {
                struct symt*    cls_dt;
                struct symt*    pmt_dt;

                PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &cls_dt) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ',');
                PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &ref_dt) == -1);
                new_dt = &symt_new_function_signature(ptd->module, ref_dt, -1)->symt;
                while (*ptd->ptr == ',')
                {
                    ptd->ptr++;
                    PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &pmt_dt) == -1);
                }
            }
            break;
        case 'R':
            {
                long    type, len, unk;
                int     basic;
                
                PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &type) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ';');	/* ';' */
                PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &len) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ';');	/* ';' */
                PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &unk) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ';');	/* ';' */

                switch (type) /* see stabs_get_basic for the details */
                {
                case 1: basic = 12; break;
                case 2: basic = 13; break;
                case 3: basic = 25; break;
                case 4: basic = 26; break;
                case 5: basic = 35; break;
                case 6: basic = 14; break;
                default: PTS_ABORTIF(ptd, 1);
                }
                PTS_ABORTIF(ptd, stabs_get_basic(ptd, basic, &new_dt) == -1);
            }
            break;
	default:
	    ERR("Unknown type '%c'\n", ptd->ptr[-1]);
	    return -1;
	}
    }

    if (!new_dt)
    {
        /* is it a forward declaration that has been filled ? */
	new_dt = *stabs_find_ref(filenr1, subnr1);
        /* if not, this should be void (which is defined as a ref to itself, but we
         * don't correctly catch it)
         */
        if (!new_dt && typename)
        {
            new_dt = &symt_new_basic(ptd->module, btVoid, typename, 0)->symt;
            PTS_ABORTIF(ptd, strcmp(typename, "void"));
        }
    }            

    *stabs_find_ref(filenr1, subnr1) = *ret_dt = new_dt;

    TRACE("Adding (%ld,%ld) %s\n", filenr1, subnr1, debugstr_a(typename));

    return 0;
}