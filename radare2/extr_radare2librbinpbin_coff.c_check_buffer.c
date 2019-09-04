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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ r_coff_supported_arch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_buffer(RBuffer *buf) {
#if 0
TODO: do more checks here to avoid false positives

ut16 MACHINE
ut16 NSECTIONS
ut32 DATE
ut32 PTRTOSYMTABLE
ut32 NUMOFSYMS
ut16 OPTHDRSIZE
ut16 CHARACTERISTICS
#endif

	ut8 tmp[20];
	int r = r_buf_read_at (buf, 0, tmp, sizeof (tmp));
	return r >= 20 && r_coff_supported_arch (tmp);
}