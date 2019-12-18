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
struct key_source {int /*<<< orphan*/  random2; int /*<<< orphan*/  random1; int /*<<< orphan*/  pre_master; } ;
struct key_source2 {struct key_source server; struct key_source client; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (struct key_source) ; 
 int /*<<< orphan*/  random_bytes_to_buf (struct buffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
key_source2_randomize_write(struct key_source2 *k2,
                            struct buffer *buf,
                            bool server)
{
    struct key_source *k = &k2->client;
    if (server)
    {
        k = &k2->server;
    }

    CLEAR(*k);

    if (!server)
    {
        if (!random_bytes_to_buf(buf, k->pre_master, sizeof(k->pre_master)))
        {
            return false;
        }
    }

    if (!random_bytes_to_buf(buf, k->random1, sizeof(k->random1)))
    {
        return false;
    }
    if (!random_bytes_to_buf(buf, k->random2, sizeof(k->random2)))
    {
        return false;
    }

    return true;
}