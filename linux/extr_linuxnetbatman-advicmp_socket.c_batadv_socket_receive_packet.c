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
struct batadv_socket_client {int dummy; } ;
struct batadv_icmp_header {size_t uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_socket_add_packet (struct batadv_socket_client*,struct batadv_icmp_header*,size_t) ; 
 struct batadv_socket_client** batadv_socket_client_hash ; 

void batadv_socket_receive_packet(struct batadv_icmp_header *icmph,
				  size_t icmp_len)
{
	struct batadv_socket_client *hash;

	hash = batadv_socket_client_hash[icmph->uid];
	if (hash)
		batadv_socket_add_packet(hash, icmph, icmp_len);
}