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
struct key {int /*<<< orphan*/  sem; } ;
struct ecryptfs_msg_ctx {int dummy; } ;
typedef  char ecryptfs_message ;
struct ecryptfs_key_record {int dummy; } ;
struct ecryptfs_crypt_stat {int /*<<< orphan*/  key_size; int /*<<< orphan*/  cipher; } ;
struct TYPE_3__ {int /*<<< orphan*/  signature; } ;
struct TYPE_4__ {TYPE_1__ private_key; } ;
struct ecryptfs_auth_tok {TYPE_2__ token; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ecryptfs_code_for_cipher_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,...) ; 
 int ecryptfs_send_message (char*,size_t,struct ecryptfs_msg_ctx**) ; 
 int ecryptfs_wait_for_response (struct ecryptfs_msg_ctx*,char**) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int parse_tag_67_packet (struct ecryptfs_key_record*,char*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int write_tag_66_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecryptfs_crypt_stat*,char**,size_t*) ; 

__attribute__((used)) static int
pki_encrypt_session_key(struct key *auth_tok_key,
			struct ecryptfs_auth_tok *auth_tok,
			struct ecryptfs_crypt_stat *crypt_stat,
			struct ecryptfs_key_record *key_rec)
{
	struct ecryptfs_msg_ctx *msg_ctx = NULL;
	char *payload = NULL;
	size_t payload_len = 0;
	struct ecryptfs_message *msg;
	int rc;

	rc = write_tag_66_packet(auth_tok->token.private_key.signature,
				 ecryptfs_code_for_cipher_string(
					 crypt_stat->cipher,
					 crypt_stat->key_size),
				 crypt_stat, &payload, &payload_len);
	up_write(&(auth_tok_key->sem));
	key_put(auth_tok_key);
	if (rc) {
		ecryptfs_printk(KERN_ERR, "Error generating tag 66 packet\n");
		goto out;
	}
	rc = ecryptfs_send_message(payload, payload_len, &msg_ctx);
	if (rc) {
		ecryptfs_printk(KERN_ERR, "Error sending message to "
				"ecryptfsd: %d\n", rc);
		goto out;
	}
	rc = ecryptfs_wait_for_response(msg_ctx, &msg);
	if (rc) {
		ecryptfs_printk(KERN_ERR, "Failed to receive tag 67 packet "
				"from the user space daemon\n");
		rc = -EIO;
		goto out;
	}
	rc = parse_tag_67_packet(key_rec, msg);
	if (rc)
		ecryptfs_printk(KERN_ERR, "Error parsing tag 67 packet\n");
	kfree(msg);
out:
	kfree(payload);
	return rc;
}