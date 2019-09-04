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
struct mp_recorder_sink {int num_packets; int /*<<< orphan*/ * packets; } ;
struct mp_recorder {int num_streams; struct mp_recorder_sink** streams; } ;

/* Variables and functions */
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_packets(struct mp_recorder *priv)
{
    for (int n = 0; n < priv->num_streams; n++) {
        struct mp_recorder_sink *rst = priv->streams[n];
        for (int i = 0; i < rst->num_packets; i++)
            talloc_free(rst->packets[i]);
        rst->num_packets = 0;
    }
}