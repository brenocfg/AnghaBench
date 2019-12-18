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
struct snd_seq_addr {scalar_t__ client; scalar_t__ port; } ;

/* Variables and functions */

__attribute__((used)) static inline int addr_match(struct snd_seq_addr *r, struct snd_seq_addr *s)
{
	return (r->client == s->client) && (r->port == s->port);
}