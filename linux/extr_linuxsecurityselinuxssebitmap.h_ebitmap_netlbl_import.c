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
struct netlbl_lsm_catmap {int dummy; } ;
struct ebitmap {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 

__attribute__((used)) static inline int ebitmap_netlbl_import(struct ebitmap *ebmap,
					struct netlbl_lsm_catmap *catmap)
{
	return -ENOMEM;
}