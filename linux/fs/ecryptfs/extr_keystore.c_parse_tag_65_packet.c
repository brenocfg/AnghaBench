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
typedef  char u8 ;
typedef  unsigned char u16 ;
struct ecryptfs_session_key {size_t decrypted_key_size; unsigned char* decrypted_key; } ;
struct ecryptfs_message {size_t data_len; char* data; } ;

/* Variables and functions */
 unsigned char ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES ; 
 size_t ECRYPTFS_MAX_KEY_BYTES ; 
 char ECRYPTFS_TAG_65_PACKET_TYPE ; 
 int EIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int ecryptfs_parse_packet_length (char*,size_t*,size_t*) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,unsigned char) ; 

__attribute__((used)) static int
parse_tag_65_packet(struct ecryptfs_session_key *session_key, u8 *cipher_code,
		    struct ecryptfs_message *msg)
{
	size_t i = 0;
	char *data;
	size_t data_len;
	size_t m_size;
	size_t message_len;
	u16 checksum = 0;
	u16 expected_checksum = 0;
	int rc;

	/*
	 *              ***** TAG 65 Packet Format *****
	 *         | Content Type             | 1 byte       |
	 *         | Status Indicator         | 1 byte       |
	 *         | File Encryption Key Size | 1 or 2 bytes |
	 *         | File Encryption Key      | arbitrary    |
	 */
	message_len = msg->data_len;
	data = msg->data;
	if (message_len < 4) {
		rc = -EIO;
		goto out;
	}
	if (data[i++] != ECRYPTFS_TAG_65_PACKET_TYPE) {
		ecryptfs_printk(KERN_ERR, "Type should be ECRYPTFS_TAG_65\n");
		rc = -EIO;
		goto out;
	}
	if (data[i++]) {
		ecryptfs_printk(KERN_ERR, "Status indicator has non-zero value "
				"[%d]\n", data[i-1]);
		rc = -EIO;
		goto out;
	}
	rc = ecryptfs_parse_packet_length(&data[i], &m_size, &data_len);
	if (rc) {
		ecryptfs_printk(KERN_WARNING, "Error parsing packet length; "
				"rc = [%d]\n", rc);
		goto out;
	}
	i += data_len;
	if (message_len < (i + m_size)) {
		ecryptfs_printk(KERN_ERR, "The message received from ecryptfsd "
				"is shorter than expected\n");
		rc = -EIO;
		goto out;
	}
	if (m_size < 3) {
		ecryptfs_printk(KERN_ERR,
				"The decrypted key is not long enough to "
				"include a cipher code and checksum\n");
		rc = -EIO;
		goto out;
	}
	*cipher_code = data[i++];
	/* The decrypted key includes 1 byte cipher code and 2 byte checksum */
	session_key->decrypted_key_size = m_size - 3;
	if (session_key->decrypted_key_size > ECRYPTFS_MAX_KEY_BYTES) {
		ecryptfs_printk(KERN_ERR, "key_size [%d] larger than "
				"the maximum key size [%d]\n",
				session_key->decrypted_key_size,
				ECRYPTFS_MAX_ENCRYPTED_KEY_BYTES);
		rc = -EIO;
		goto out;
	}
	memcpy(session_key->decrypted_key, &data[i],
	       session_key->decrypted_key_size);
	i += session_key->decrypted_key_size;
	expected_checksum += (unsigned char)(data[i++]) << 8;
	expected_checksum += (unsigned char)(data[i++]);
	for (i = 0; i < session_key->decrypted_key_size; i++)
		checksum += session_key->decrypted_key[i];
	if (expected_checksum != checksum) {
		ecryptfs_printk(KERN_ERR, "Invalid checksum for file "
				"encryption  key; expected [%x]; calculated "
				"[%x]\n", expected_checksum, checksum);
		rc = -EIO;
	}
out:
	return rc;
}