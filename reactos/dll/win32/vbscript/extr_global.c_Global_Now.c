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
typedef  int /*<<< orphan*/  vbdisp_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetLocalTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemTimeToVariantTime (int /*<<< orphan*/ *,double*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  return_date (int /*<<< orphan*/ *,double) ; 

__attribute__((used)) static HRESULT Global_Now(vbdisp_t *This, VARIANT *arg, unsigned args_cnt, VARIANT *res)
{
    SYSTEMTIME lt;
    double date;

    TRACE("\n");

    GetLocalTime(&lt);
    SystemTimeToVariantTime(&lt, &date);
    return return_date(res, date);
}