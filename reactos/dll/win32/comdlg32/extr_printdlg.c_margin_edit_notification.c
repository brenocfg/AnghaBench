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
typedef  int /*<<< orphan*/  pagesetup_data ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  EN_CHANGE 129 
#define  EN_KILLFOCUS 128 
 int /*<<< orphan*/  GetDlgItemTextW (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* element_from_margin_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_decimal_sep () ; 
 int /*<<< orphan*/  is_metric (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  iswdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagesetup_get_margin_rect (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  update_margin_edits (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int wcstol (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void margin_edit_notification(HWND hDlg, const pagesetup_data *data, WORD msg, WORD id)
{
    switch (msg)
    {
    case EN_CHANGE:
      {
        WCHAR buf[10];
        LONG val = 0;
        LONG *value = element_from_margin_id(pagesetup_get_margin_rect(data), id);

        if (GetDlgItemTextW(hDlg, id, buf, ARRAY_SIZE(buf)) != 0)
        {
            WCHAR *end;
            WCHAR decimal = get_decimal_sep();

            val = wcstol(buf, &end, 10);
            if(end != buf || *end == decimal)
            {
                int mult = is_metric(data) ? 100 : 1000;
                val *= mult;
                if(*end == decimal)
                {
                    while(mult > 1)
                    {
                        end++;
                        mult /= 10;
                        if(iswdigit(*end))
                            val += (*end - '0') * mult;
                        else
                            break;
                    }
                }
            }
        }
        *value = val;
        return;
      }

    case EN_KILLFOCUS:
        update_margin_edits(hDlg, data, id);
        return;
    }
}