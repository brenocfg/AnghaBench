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
struct SN_env {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int len_utf8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_has_min_length(struct SN_env * z) { /* forwardmode */
    if (!(len_utf8(z->p) > 4)) return 0; /* $(<integer expression> > <integer expression>), line 100 */
    return 1;
}