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
struct snd_seq_client_info {scalar_t__ client; } ;
struct snd_seq_client {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ SNDRV_SEQ_MAX_CLIENTS ; 
 int /*<<< orphan*/  get_client_info (struct snd_seq_client*,struct snd_seq_client_info*) ; 
 int /*<<< orphan*/  snd_seq_client_unlock (struct snd_seq_client*) ; 
 struct snd_seq_client* snd_seq_client_use_ptr (scalar_t__) ; 

__attribute__((used)) static int snd_seq_ioctl_query_next_client(struct snd_seq_client *client,
					   void *arg)
{
	struct snd_seq_client_info *info = arg;
	struct snd_seq_client *cptr = NULL;

	/* search for next client */
	if (info->client < INT_MAX)
		info->client++;
	if (info->client < 0)
		info->client = 0;
	for (; info->client < SNDRV_SEQ_MAX_CLIENTS; info->client++) {
		cptr = snd_seq_client_use_ptr(info->client);
		if (cptr)
			break; /* found */
	}
	if (cptr == NULL)
		return -ENOENT;

	get_client_info(cptr, info);
	snd_seq_client_unlock(cptr);

	return 0;
}