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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  _transp (int /*<<< orphan*/ *,int,int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2p_unsupported () ; 
 int /*<<< orphan*/  get_mask (unsigned int) ; 

__attribute__((used)) static inline void transp4x(u32 d[], unsigned int n, unsigned int m)
{
	u32 mask = get_mask(n);

	switch (m) {
	case 2:
		/* Single n x 2 block */
		_transp(d, 2, 0, n, mask);
		_transp(d, 3, 1, n, mask);
		return;
	}

	c2p_unsupported();
}