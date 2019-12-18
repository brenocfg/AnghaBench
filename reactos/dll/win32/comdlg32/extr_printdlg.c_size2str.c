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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  get_decimal_sep () ; 
 scalar_t__ is_metric (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wsprintfW (int /*<<< orphan*/ ,char const*,int,...) ; 

__attribute__((used)) static void size2str(const pagesetup_data *data, DWORD size, LPWSTR strout)
{
    static const WCHAR integer_fmt[] = {'%','d',0};
    static const WCHAR hundredths_fmt[] = {'%','d','%','c','%','0','2','d',0};
    static const WCHAR thousandths_fmt[] = {'%','d','%','c','%','0','3','d',0};

    /* FIXME use LOCALE_SDECIMAL when the edit parsing code can cope */

    if (is_metric(data))
    {
        if(size % 100)
            wsprintfW(strout, hundredths_fmt, size / 100, get_decimal_sep(), size % 100);
        else
            wsprintfW(strout, integer_fmt, size / 100);
    }
    else
    {
        if(size % 1000)
            wsprintfW(strout, thousandths_fmt, size / 1000, get_decimal_sep(), size % 1000);
        else
            wsprintfW(strout, integer_fmt, size / 1000);

    }
}