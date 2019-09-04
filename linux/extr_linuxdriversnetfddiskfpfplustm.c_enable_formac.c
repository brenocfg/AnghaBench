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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_IMSK1L ; 
 int /*<<< orphan*/  FM_IMSK1U ; 
 int /*<<< orphan*/  FM_IMSK2L ; 
 int /*<<< orphan*/  FM_IMSK2U ; 
 int /*<<< orphan*/  FM_IMSK3L ; 
 int /*<<< orphan*/  FM_IMSK3U ; 
 scalar_t__ mac_imsk1l ; 
 scalar_t__ mac_imsk1u ; 
 scalar_t__ mac_imsk2l ; 
 scalar_t__ mac_imsk2u ; 
 scalar_t__ mac_imsk3l ; 
 scalar_t__ mac_imsk3u ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void enable_formac(struct s_smc *smc)
{
	/* set formac IMSK : 0 enables irq */
	outpw(FM_A(FM_IMSK1U),(unsigned short)~mac_imsk1u);
	outpw(FM_A(FM_IMSK1L),(unsigned short)~mac_imsk1l);
	outpw(FM_A(FM_IMSK2U),(unsigned short)~mac_imsk2u);
	outpw(FM_A(FM_IMSK2L),(unsigned short)~mac_imsk2l);
	outpw(FM_A(FM_IMSK3U),(unsigned short)~mac_imsk3u);
	outpw(FM_A(FM_IMSK3L),(unsigned short)~mac_imsk3l);
}