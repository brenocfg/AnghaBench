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
struct nvenc_data {size_t buf_count; int /*<<< orphan*/  bitstreams; } ;
struct nv_bitstream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct nv_bitstream*) ; 
 int /*<<< orphan*/  da_reserve (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nv_bitstream_init (struct nvenc_data*,struct nv_bitstream*) ; 

__attribute__((used)) static bool init_bitstreams(struct nvenc_data *enc)
{
	da_reserve(enc->bitstreams, enc->buf_count);
	for (size_t i = 0; i < enc->buf_count; i++) {
		struct nv_bitstream bitstream;
		if (!nv_bitstream_init(enc, &bitstream)) {
			return false;
		}

		da_push_back(enc->bitstreams, &bitstream);
	}

	return true;
}