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
typedef  int /*<<< orphan*/  uint32_t ;
struct ead_msg_encrypted {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  W ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sha_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha_transform (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ead_hash_message(struct ead_msg_encrypted *enc, uint32_t *hash, int len)
{
	unsigned char *data = (unsigned char *) enc;

	/* hash the packet with the stored hash part initialized to zero */
	sha_init(hash);
	memset(enc->hash, 0, sizeof(enc->hash));
	while (len > 0) {
		sha_transform(hash, data, W);
		len -= 64;
		data += 64;
	}
}