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
struct m66592 {int dummy; } ;

/* Variables and functions */
 int M66592_BEMPE ; 
 int M66592_BRDYE ; 
 int M66592_CMPL ; 
 int M66592_CTRE ; 
 int M66592_DPRPU ; 
 int /*<<< orphan*/  M66592_INTENB0 ; 
 int M66592_RDST ; 
 int /*<<< orphan*/  M66592_SYSCFG ; 
 int M66592_WDST ; 
 int /*<<< orphan*/  m66592_bset (struct m66592*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m66592_usb_connect(struct m66592 *m66592)
{
	m66592_bset(m66592, M66592_CTRE, M66592_INTENB0);
	m66592_bset(m66592, M66592_WDST | M66592_RDST | M66592_CMPL,
			M66592_INTENB0);
	m66592_bset(m66592, M66592_BEMPE | M66592_BRDYE, M66592_INTENB0);

	m66592_bset(m66592, M66592_DPRPU, M66592_SYSCFG);
}