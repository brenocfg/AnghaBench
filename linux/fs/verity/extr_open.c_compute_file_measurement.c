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
typedef  int /*<<< orphan*/  u8 ;
struct fsverity_hash_alg {int dummy; } ;
struct fsverity_descriptor {int /*<<< orphan*/  sig_size; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int fsverity_hash_buffer (struct fsverity_hash_alg const*,struct fsverity_descriptor*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int compute_file_measurement(const struct fsverity_hash_alg *hash_alg,
				    struct fsverity_descriptor *desc,
				    u8 *measurement)
{
	__le32 sig_size = desc->sig_size;
	int err;

	desc->sig_size = 0;
	err = fsverity_hash_buffer(hash_alg, desc, sizeof(*desc), measurement);
	desc->sig_size = sig_size;

	return err;
}