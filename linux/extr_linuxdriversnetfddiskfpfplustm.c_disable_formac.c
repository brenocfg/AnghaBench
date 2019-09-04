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
 int /*<<< orphan*/  MW ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_formac(struct s_smc *smc)
{
	/* clear formac IMSK : 1 disables irq */
	outpw(FM_A(FM_IMSK1U),MW) ;
	outpw(FM_A(FM_IMSK1L),MW) ;
	outpw(FM_A(FM_IMSK2U),MW) ;
	outpw(FM_A(FM_IMSK2L),MW) ;
	outpw(FM_A(FM_IMSK3U),MW) ;
	outpw(FM_A(FM_IMSK3L),MW) ;
}