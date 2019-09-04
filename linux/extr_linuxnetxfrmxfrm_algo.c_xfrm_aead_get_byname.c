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
struct xfrm_algo_desc {int dummy; } ;
struct xfrm_aead_name {char const* name; int icvbits; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfrm_aead_list ; 
 int /*<<< orphan*/  xfrm_aead_name_match ; 
 struct xfrm_algo_desc* xfrm_find_algo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct xfrm_aead_name*,int) ; 

struct xfrm_algo_desc *xfrm_aead_get_byname(const char *name, int icv_len, int probe)
{
	struct xfrm_aead_name data = {
		.name = name,
		.icvbits = icv_len,
	};

	return xfrm_find_algo(&xfrm_aead_list, xfrm_aead_name_match, &data,
			      probe);
}