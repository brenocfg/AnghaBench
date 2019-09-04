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
struct smb2_sync_hdr {int /*<<< orphan*/  MessageId; int /*<<< orphan*/  CreditCharge; } ;
struct TCP_Server_Info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_next_mid (struct TCP_Server_Info*) ; 
 int /*<<< orphan*/  get_next_mid64 (struct TCP_Server_Info*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
smb2_seq_num_into_buf(struct TCP_Server_Info *server,
		      struct smb2_sync_hdr *shdr)
{
	unsigned int i, num = le16_to_cpu(shdr->CreditCharge);

	shdr->MessageId = get_next_mid64(server);
	/* skip message numbers according to CreditCharge field */
	for (i = 1; i < num; i++)
		get_next_mid(server);
}