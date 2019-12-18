#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WPARAM ;
struct TYPE_6__ {int style; } ;
struct TYPE_5__ {int styleNew; } ;
typedef  TYPE_1__ STYLESTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_2__ EDITSTATE ;
typedef  int DWORD ;

/* Variables and functions */
 int ES_LOWERCASE ; 
 int ES_MULTILINE ; 
 int ES_NUMBER ; 
 int ES_UPPERCASE ; 
 int ES_WANTRETURN ; 
 scalar_t__ GWL_EXSTYLE ; 
 scalar_t__ GWL_STYLE ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 

__attribute__((used)) static LRESULT  EDIT_WM_StyleChanged ( EDITSTATE *es, WPARAM which, const STYLESTRUCT *style)
{
        if (GWL_STYLE == which) {
                DWORD style_change_mask;
                DWORD new_style;
                /* Only a subset of changes can be applied after the control
                 * has been created.
                 */
                style_change_mask = ES_UPPERCASE | ES_LOWERCASE |
                                    ES_NUMBER;
                if (es->style & ES_MULTILINE)
                        style_change_mask |= ES_WANTRETURN;

                new_style = style->styleNew & style_change_mask;

                /* Number overrides lowercase overrides uppercase (at least it
                 * does in Win95).  However I'll bet that ES_NUMBER would be
                 * invalid under Win 3.1.
                 */
                if (new_style & ES_NUMBER) {
                        ; /* do not override the ES_NUMBER */
                }  else if (new_style & ES_LOWERCASE) {
                        new_style &= ~ES_UPPERCASE;
                }

                es->style = (es->style & ~style_change_mask) | new_style;
        } else if (GWL_EXSTYLE == which) {
                ; /* FIXME - what is needed here */
        } else {
                WARN ("Invalid style change %ld\n",which);
        }

        return 0;
}