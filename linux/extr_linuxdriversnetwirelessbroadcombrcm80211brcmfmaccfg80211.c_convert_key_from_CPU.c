#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lo; void* hi; } ;
struct brcmf_wsec_key_le {int /*<<< orphan*/  ea; int /*<<< orphan*/  data; void* iv_initialized; TYPE_1__ rxiv; void* flags; void* algo; void* len; void* index; } ;
struct TYPE_4__ {int /*<<< orphan*/  lo; int /*<<< orphan*/  hi; } ;
struct brcmf_wsec_key {int /*<<< orphan*/  ea; int /*<<< orphan*/  data; int /*<<< orphan*/  iv_initialized; TYPE_2__ rxiv; int /*<<< orphan*/  flags; int /*<<< orphan*/  algo; int /*<<< orphan*/  len; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void convert_key_from_CPU(struct brcmf_wsec_key *key,
				 struct brcmf_wsec_key_le *key_le)
{
	key_le->index = cpu_to_le32(key->index);
	key_le->len = cpu_to_le32(key->len);
	key_le->algo = cpu_to_le32(key->algo);
	key_le->flags = cpu_to_le32(key->flags);
	key_le->rxiv.hi = cpu_to_le32(key->rxiv.hi);
	key_le->rxiv.lo = cpu_to_le16(key->rxiv.lo);
	key_le->iv_initialized = cpu_to_le32(key->iv_initialized);
	memcpy(key_le->data, key->data, sizeof(key->data));
	memcpy(key_le->ea, key->ea, sizeof(key->ea));
}