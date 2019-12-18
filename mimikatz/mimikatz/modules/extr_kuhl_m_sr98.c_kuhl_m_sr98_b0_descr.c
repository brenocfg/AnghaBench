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
typedef  int ULONG ;
typedef  int UCHAR ;
typedef  int /*<<< orphan*/  PCWCHAR ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/ * kuhl_m_sr98_b0_descr_basic_rf ; 
 int /*<<< orphan*/ * kuhl_m_sr98_b0_descr_pskcf_rf ; 

void kuhl_m_sr98_b0_descr(ULONG b0)
{
	UCHAR XMode = (b0 >> 17) & 1, n = (b0 >> 28) & 0xf, i;
	BOOLEAN isMasterKey69 = (n == 6) || (n == 9), isExtended = XMode && isMasterKey69;
	PCWCHAR pModulation;

	kprintf(L"\nT5577 Config block\n==================\nBlock[0]             : 0x%08x\nTest mode            : %s\nExtended mode        : %s\n\nMaster Key           : %hhu (0x%1x)\n", b0, (n == 6) ? L"DISABLED" : L"ENABLED", isExtended ? L"YES" : L"NO", n, n);
	if(isExtended)
	{
		if((b0 >> 24) & 0xf)
			PRINT_ERROR(L"Invalid configuration bits in [5-8]\n");
		n = ((b0 >> 18) & 0x3f);
		kprintf(L"Data Bit Rate        : RF/%hhu (%hhu)\n", 2*n+2, n);
	}
	else
	{
		if((b0 >> 21) & 0x7f)
			PRINT_ERROR(L"Invalid configuration bits in [5-11]\n");
		n = (b0 >> 18) & 0x7;
		kprintf(L"Data Bit Rate        : RF/%hhu (%hhu)\n", kuhl_m_sr98_b0_descr_basic_rf[n], n);
	}
	kprintf(L"X-Mode               : %s\n", XMode ? L"YES" : L"NO");
	if(XMode && !isExtended)
		PRINT_ERROR(L"X-mode bit is set, but not in Extended mode (because of the Master Key)\n");
	n = (b0 >> 12) & 0x1f;
	switch(n)
	{
	case 0: pModulation = L"Direct"; break;
	case 1: pModulation = L"PSK1"; break;
	case 2: pModulation = L"PSK2"; break;
	case 3: pModulation = L"PSK3"; break;
	case 4: pModulation = L"FSK1"; break;
	case 5: pModulation = L"FSK2"; break;
	case 6: pModulation = L"FSK1a"; break;
	case 7: pModulation = L"FSK2a"; break;
	case 8: pModulation = L"Manchester"; break;
	case 16: pModulation = L"Bi-phase"; break;
	case 24: pModulation = L"Differential bi-phase"; break;
	default: pModulation = L"INVALID";
	}
	kprintf(L"Modulation           : %s (%hhu)\n", pModulation, n);
	if(((n == 24) && !isExtended) || (((n == 6) || (n == 7)) && isExtended))
		PRINT_ERROR(L"Invalid Modulation in this mode\n");
	i = (b0 >> 10) & 0x3;
	n = (b0 >> 5) & 0x7;
	kprintf(L"PSK Clock Frequency  : %s (%hhu)\nAnswer On Request    : %s\nOne Time Password    : %s\nMaxblock             : %hhu ( ", kuhl_m_sr98_b0_descr_pskcf_rf[i], i, ((b0 >> 9) & 1) ? L"YES" : L"NO", ((b0 >> 8) & 1) ? L"YES" : L"NO", n);
	for(i = 1; i <= n; i++)
		kprintf(L"B[%hhu] ", i);
	i = ((b0 >> 4) & 1);
	kprintf(L")\nPassword             : %s\n", i ? L"YES" : L"NO");
	if(i && (n == 7))
		PRINT_ERROR(L"Password can be transmitted on the wire because of Maxblock\n");
	if(isExtended)
		kprintf(L"Sequence Start Marker: %s\nFast Downlink        : %s\nInverse Data         : %s\n", ((b0 >> 3) & 1) ? L"YES" : L"NO", ((b0 >> 2) & 1) ? L"YES" : L"NO", ((b0 >> 1) & 1) ? L"YES" : L"NO");
	else
	{
		kprintf(L"Sequence Terminator  : %s\n", ((b0 >> 3) & 1) ? L"YES" : L"NO");
		if((b0 >> 1) & 0x3)
			PRINT_ERROR(L"Invalid configuration bits in [30-31]\n");
	}
	n = b0 & 1;
	kprintf(L"Init Delay           : %s\n", n ? L"YES" : L"NO");
	if(n & !isMasterKey69)
		PRINT_ERROR(L"Init Delay bit is set, but was disabled (because of the Master Key)\n");
}