#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ ELFOBJ ;

/* Variables and functions */
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_mem_mem (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline int noodle(ELFOBJ *bin, const char *s) {
	if (r_buf_size (bin->b) <= 64)  {
		return 0;
	}
	ut8 tmp[64];
	r_buf_read_at (bin->b, r_buf_size (bin->b) - 64, tmp, 64);
	return r_mem_mem (tmp, 64, (const ut8 *)s, strlen (s)) != NULL;
}