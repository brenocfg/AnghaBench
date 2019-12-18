#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msi_maskedit_info {int num_chars; size_t num_groups; TYPE_2__* dialog; scalar_t__* prop; TYPE_1__* group; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_4__ {int /*<<< orphan*/  package; } ;
struct TYPE_3__ {unsigned int len; int /*<<< orphan*/  hwnd; scalar_t__ type; } ;
typedef  scalar_t__* LPWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,size_t) ; 
 size_t GetWindowTextW (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 size_t SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,size_t,size_t) ; 
 int /*<<< orphan*/  WM_GETTEXTLENGTH ; 
 size_t debugstr_w (scalar_t__*) ; 
 scalar_t__* msi_alloc (int) ; 
 int /*<<< orphan*/  msi_dialog_evaluate_control_conditions (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_dialog_set_property (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 
 int /*<<< orphan*/  msi_mask_editable (scalar_t__) ; 
 scalar_t__* msi_realloc (scalar_t__*,size_t) ; 

__attribute__((used)) static void msi_mask_control_change( struct msi_maskedit_info *info )
{
    LPWSTR val;
    UINT i, n, r;

    val = msi_alloc( (info->num_chars+1)*sizeof(WCHAR) );
    for( i=0, n=0; i<info->num_groups; i++ )
    {
        if (info->group[i].len == ~0u)
        {
            UINT len = SendMessageW( info->group[i].hwnd, WM_GETTEXTLENGTH, 0, 0 );
            val = msi_realloc( val, (len + 1) * sizeof(WCHAR) );
            GetWindowTextW( info->group[i].hwnd, val, len + 1 );
        }
        else
        {
            if (info->group[i].len + n > info->num_chars)
            {
                ERR("can't fit control %d text into template\n",i);
                break;
            }
            if (!msi_mask_editable(info->group[i].type))
            {
                for(r=0; r<info->group[i].len; r++)
                    val[n+r] = info->group[i].type;
                val[n+r] = 0;
            }
            else
            {
                r = GetWindowTextW( info->group[i].hwnd, &val[n], info->group[i].len+1 );
                if( r != info->group[i].len )
                    break;
            }
            n += r;
        }
    }

    TRACE("%d/%d controls were good\n", i, info->num_groups);

    if( i == info->num_groups )
    {
        TRACE("Set property %s to %s\n", debugstr_w(info->prop), debugstr_w(val));
        msi_dialog_set_property( info->dialog->package, info->prop, val );
        msi_dialog_evaluate_control_conditions( info->dialog );
    }
    msi_free( val );
}