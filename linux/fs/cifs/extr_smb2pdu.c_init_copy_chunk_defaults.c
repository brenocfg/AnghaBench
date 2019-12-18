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
struct cifs_tcon {int max_chunks; int max_bytes_chunk; int max_bytes_copy; } ;

/* Variables and functions */

__attribute__((used)) static inline void init_copy_chunk_defaults(struct cifs_tcon *tcon)
{
	tcon->max_chunks = 256;
	tcon->max_bytes_chunk = 1048576;
	tcon->max_bytes_copy = 16777216;
}