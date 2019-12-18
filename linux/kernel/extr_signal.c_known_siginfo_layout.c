#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int limit; } ;

/* Variables and functions */
 int NSIGPOLL ; 
 int SI_ASYNCNL ; 
 int SI_DETHREAD ; 
 int SI_KERNEL ; 
 int SI_USER ; 
 TYPE_1__* sig_sicodes ; 
 scalar_t__ sig_specific_sicodes (unsigned int) ; 

__attribute__((used)) static bool known_siginfo_layout(unsigned sig, int si_code)
{
	if (si_code == SI_KERNEL)
		return true;
	else if ((si_code > SI_USER)) {
		if (sig_specific_sicodes(sig)) {
			if (si_code <= sig_sicodes[sig].limit)
				return true;
		}
		else if (si_code <= NSIGPOLL)
			return true;
	}
	else if (si_code >= SI_DETHREAD)
		return true;
	else if (si_code == SI_ASYNCNL)
		return true;
	return false;
}