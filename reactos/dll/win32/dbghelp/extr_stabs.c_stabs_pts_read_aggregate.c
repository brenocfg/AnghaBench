#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct symt_udt {int dummy; } ;
struct symt {int dummy; } ;
struct ParseTypedefData {char* ptr; int idx; int /*<<< orphan*/  buf; int /*<<< orphan*/  module; } ;
typedef  scalar_t__ DWORD64 ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  PTS_ABORTIF (struct ParseTypedefData*,int) ; 
 int /*<<< orphan*/  TI_GET_LENGTH ; 
 int TRUE ; 
 int stabs_pts_read_id (struct ParseTypedefData*) ; 
 int /*<<< orphan*/  stabs_pts_read_method_info (struct ParseTypedefData*) ; 
 int stabs_pts_read_number (struct ParseTypedefData*,long*) ; 
 int stabs_pts_read_type_def (struct ParseTypedefData*,int /*<<< orphan*/ *,struct symt**) ; 
 int /*<<< orphan*/  stabs_read_type_enum (float**) ; 
 int /*<<< orphan*/  strcat (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  symt_add_udt_element (int /*<<< orphan*/ ,struct symt_udt*,char*,struct symt*,long,long) ; 
 int /*<<< orphan*/  symt_get_info (int /*<<< orphan*/ ,struct symt*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  symt_get_name (struct symt*) ; 
 int symt_set_udt_size (int /*<<< orphan*/ ,struct symt_udt*,long) ; 

__attribute__((used)) static inline int stabs_pts_read_aggregate(struct ParseTypedefData* ptd, 
                                           struct symt_udt* sdt)
{
    long        	sz, ofs;
    struct symt*        adt;
    struct symt*        dt = NULL;
    int			idx;
    int			doadd;

    PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &sz) == -1);

    doadd = symt_set_udt_size(ptd->module, sdt, sz);
    if (*ptd->ptr == '!') /* C++ inheritance */
    {
        long     num_classes;

        ptd->ptr++;
        PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &num_classes) == -1);
        PTS_ABORTIF(ptd, *ptd->ptr++ != ',');
        while (--num_classes >= 0)
        {
            ptd->ptr += 2; /* skip visibility and inheritance */
            PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &ofs) == -1);
            PTS_ABORTIF(ptd, *ptd->ptr++ != ',');

            PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &adt) == -1);

            if (doadd && adt)
            {
                char    tmp[256];
                DWORD64 size;

                strcpy(tmp, "__inherited_class_");
                strcat(tmp, symt_get_name(adt));

                /* FIXME: TI_GET_LENGTH will not always work, especially when adt
                 * has just been seen as a forward definition and not the real stuff
                 * yet.
                 * As we don't use much the size of members in structs, this may not
                 * be much of a problem
                 */
                symt_get_info(ptd->module, adt, TI_GET_LENGTH, &size);
                symt_add_udt_element(ptd->module, sdt, tmp, adt, ofs, (DWORD)size * 8);
            }
            PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
        }
        
    }
    /* if the structure has already been filled, just redo the parsing
     * but don't store results into the struct
     * FIXME: there's a quite ugly memory leak in there...
     */

    /* Now parse the individual elements of the structure/union. */
    while (*ptd->ptr != ';') 
    {
	/* agg_name : type ',' <int:offset> ',' <int:size> */
	idx = ptd->idx;

        if (ptd->ptr[0] == '$' && ptd->ptr[1] == 'v')
        {
            long        x;

            if (ptd->ptr[2] == 'f')
            {
                /* C++ virtual method table */
                ptd->ptr += 3;
                stabs_read_type_enum(&ptd->ptr);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ':');
                PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &dt) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ',');
                PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &x) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
                ptd->idx = idx;
                continue;
            }
            else if (ptd->ptr[2] == 'b')
            {
                ptd->ptr += 3;
                PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &dt) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ':');
                PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &dt) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ',');
                PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &x) == -1);
                PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
                ptd->idx = idx;
                continue;
            }
        }

	PTS_ABORTIF(ptd, stabs_pts_read_id(ptd) == -1);
        /* Ref. TSDF R2.130 Section 7.4.  When the field name is a method name
         * it is followed by two colons rather than one.
         */
        if (*ptd->ptr == ':')
        {
            ptd->ptr++; 
            stabs_pts_read_method_info(ptd);
            ptd->idx = idx;
            continue;
        }
        else
        {
            /* skip C++ member protection /0 /1 or /2 */
            if (*ptd->ptr == '/') ptd->ptr += 2;
        }
	PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &adt) == -1);

        switch (*ptd->ptr++)
        {
        case ',':
            PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &ofs) == -1);
            PTS_ABORTIF(ptd, *ptd->ptr++ != ',');
            PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &sz) == -1);
            PTS_ABORTIF(ptd, *ptd->ptr++ != ';');

            if (doadd) symt_add_udt_element(ptd->module, sdt, ptd->buf + idx, adt, ofs, sz);
            break;
        case ':':
            {
                const char* tmp;
                /* method parameters... terminated by ';' */
                PTS_ABORTIF(ptd, !(tmp = strchr(ptd->ptr, ';')));
                ptd->ptr = tmp + 1;
            }
            break;
        default:
            PTS_ABORTIF(ptd, TRUE);
        }
	ptd->idx = idx;
    }
    PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
    if (*ptd->ptr == '~')
    {
        ptd->ptr++;
        PTS_ABORTIF(ptd, *ptd->ptr++ != '%');
        PTS_ABORTIF(ptd, stabs_pts_read_type_def(ptd, NULL, &dt) == -1);
        PTS_ABORTIF(ptd, *ptd->ptr++ != ';');
    }
    return 0;
}