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
typedef  int SID_NAME_USE ;
typedef  char* PCWCHAR ;

/* Variables and functions */
 char** SidNameUses ; 
 int SidTypeLabel ; 

PCWCHAR kull_m_token_getSidNameUse(SID_NAME_USE SidNameUse)
{
	return (SidNameUse > 0 && SidNameUse <= SidTypeLabel) ? SidNameUses[SidNameUse - 1] : L"unk!";
}