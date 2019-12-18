#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Buffer; } ;
typedef  int /*<<< orphan*/  PCUNICODE_STRING ;
typedef  int /*<<< orphan*/  BerElement ;
typedef  TYPE_1__ ANSI_STRING ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY_ASN1_ID_GENERAL_STRING ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeAnsiString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlUnicodeStringToAnsiString (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ber_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kull_m_asn1_GenString(BerElement * pBer, PCUNICODE_STRING String)
{
	ANSI_STRING aString;
	if(NT_SUCCESS(RtlUnicodeStringToAnsiString(&aString, String, TRUE)))
	{
		ber_printf(pBer, "to", DIRTY_ASN1_ID_GENERAL_STRING, aString.Buffer, aString.Length);
		RtlFreeAnsiString(&aString);
	}
}