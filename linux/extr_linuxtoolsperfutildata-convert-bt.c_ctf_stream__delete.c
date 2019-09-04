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
struct ctf_stream {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_ctf_stream_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ctf_stream*) ; 

__attribute__((used)) static void ctf_stream__delete(struct ctf_stream *cs)
{
	if (cs) {
		bt_ctf_stream_put(cs->stream);
		free(cs);
	}
}