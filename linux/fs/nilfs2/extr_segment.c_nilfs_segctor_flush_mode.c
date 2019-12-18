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
struct nilfs_sc_info {int sc_flush_request; scalar_t__ sc_mjcp_freq; scalar_t__ sc_lseg_stime; int /*<<< orphan*/  sc_flags; } ;

/* Variables and functions */
 int FLUSH_DAT_BIT ; 
 int FLUSH_FILE_BIT ; 
 int /*<<< orphan*/  NILFS_SC_UNCLOSED ; 
 int SC_FLUSH_DAT ; 
 int SC_FLUSH_FILE ; 
 int SC_LSEG_SR ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nilfs_segctor_flush_mode(struct nilfs_sc_info *sci)
{
	if (!test_bit(NILFS_SC_UNCLOSED, &sci->sc_flags) ||
	    time_before(jiffies, sci->sc_lseg_stime + sci->sc_mjcp_freq)) {
		if (!(sci->sc_flush_request & ~FLUSH_FILE_BIT))
			return SC_FLUSH_FILE;
		else if (!(sci->sc_flush_request & ~FLUSH_DAT_BIT))
			return SC_FLUSH_DAT;
	}
	return SC_LSEG_SR;
}