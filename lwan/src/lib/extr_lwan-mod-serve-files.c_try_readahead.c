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
struct serve_files_priv {size_t read_ahead; } ;

/* Variables and functions */
 scalar_t__ LIKELY (size_t) ; 
 int /*<<< orphan*/  lwan_readahead_queue (int,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
try_readahead(const struct serve_files_priv *priv, int fd, size_t size)
{
    if (size > priv->read_ahead)
        size = priv->read_ahead;

    if (LIKELY(size))
        lwan_readahead_queue(fd, 0, size);
}