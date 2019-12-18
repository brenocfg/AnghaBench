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
struct hlist_head {int dummy; } ;

/* Variables and functions */
 unsigned long UNIX_HASH_SIZE ; 
 struct hlist_head* unix_socket_table ; 

__attribute__((used)) static struct hlist_head *unix_sockets_unbound(void *addr)
{
	unsigned long hash = (unsigned long)addr;

	hash ^= hash >> 16;
	hash ^= hash >> 8;
	hash %= UNIX_HASH_SIZE;
	return &unix_socket_table[UNIX_HASH_SIZE + hash];
}