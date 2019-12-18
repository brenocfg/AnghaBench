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
struct sock {int dummy; } ;
struct bpf_sk_storage_data {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  SELEM (struct bpf_sk_storage_data*) ; 
 int /*<<< orphan*/  selem_unlink (int /*<<< orphan*/ ) ; 
 struct bpf_sk_storage_data* sk_storage_lookup (struct sock*,struct bpf_map*,int) ; 

__attribute__((used)) static int sk_storage_delete(struct sock *sk, struct bpf_map *map)
{
	struct bpf_sk_storage_data *sdata;

	sdata = sk_storage_lookup(sk, map, false);
	if (!sdata)
		return -ENOENT;

	selem_unlink(SELEM(sdata));

	return 0;
}