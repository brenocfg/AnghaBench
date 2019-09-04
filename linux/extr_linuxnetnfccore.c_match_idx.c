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
struct nfc_dev {unsigned int const idx; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct nfc_dev* to_nfc_dev (struct device*) ; 

__attribute__((used)) static int match_idx(struct device *d, const void *data)
{
	struct nfc_dev *dev = to_nfc_dev(d);
	const unsigned int *idx = data;

	return dev->idx == *idx;
}