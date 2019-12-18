#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {int /*<<< orphan*/  wSecond; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/  PFILETIME ;
typedef  int /*<<< orphan*/  BerElement ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY_ASN1_ID_GENERALIZED_TIME ; 
 scalar_t__ FileTimeToSystemTime (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ber_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sprintf_s (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kull_m_asn1_GenTime(BerElement * pBer, PFILETIME localtime)
{
	SYSTEMTIME st;
	char buffer[4 + 2 + 2 + 2 + 2 + 2 + 1 + 1];
	if(FileTimeToSystemTime(localtime, &st))
		if(sprintf_s(buffer, sizeof(buffer), "%04hu%02hu%02hu%02hu%02hu%02huZ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond) > 0)
			ber_printf(pBer, "to", DIRTY_ASN1_ID_GENERALIZED_TIME, buffer, sizeof(buffer) - 1);
}