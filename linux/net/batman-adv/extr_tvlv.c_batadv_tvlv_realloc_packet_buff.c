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

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static bool batadv_tvlv_realloc_packet_buff(unsigned char **packet_buff,
					    int *packet_buff_len,
					    int min_packet_len,
					    int additional_packet_len)
{
	unsigned char *new_buff;

	new_buff = kmalloc(min_packet_len + additional_packet_len, GFP_ATOMIC);

	/* keep old buffer if kmalloc should fail */
	if (!new_buff)
		return false;

	memcpy(new_buff, *packet_buff, min_packet_len);
	kfree(*packet_buff);
	*packet_buff = new_buff;
	*packet_buff_len = min_packet_len + additional_packet_len;

	return true;
}