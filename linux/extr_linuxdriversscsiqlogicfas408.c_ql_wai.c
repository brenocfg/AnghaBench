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
struct qlogicfas408_priv {int qbase; int qabort; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_ERROR ; 
 int DID_PARITY ; 
 int DID_RESET ; 
 int DID_TIME_OUT ; 
 unsigned long WATCHDOG ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inb (int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  ql_zap (struct qlogicfas408_priv*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ql_wai(struct qlogicfas408_priv *priv)
{
	int k;
	int qbase = priv->qbase;
	unsigned long i;

	k = 0;
	i = jiffies + WATCHDOG;
	while (time_before(jiffies, i) && !priv->qabort &&
					!((k = inb(qbase + 4)) & 0xe0)) {
		barrier();
		cpu_relax();
	}
	if (time_after_eq(jiffies, i))
		return (DID_TIME_OUT);
	if (priv->qabort)
		return (priv->qabort == 1 ? DID_ABORT : DID_RESET);
	if (k & 0x60)
		ql_zap(priv);
	if (k & 0x20)
		return (DID_PARITY);
	if (k & 0x40)
		return (DID_ERROR);
	return 0;
}