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
struct sd_ass_priv {int num_seen_packets; scalar_t__* seen_packets; } ;
struct sd {struct sd_ass_priv* priv; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_INSERT_AT (struct sd_ass_priv*,scalar_t__*,int,int,scalar_t__) ; 

__attribute__((used)) static bool check_packet_seen(struct sd *sd, int64_t pos)
{
    struct sd_ass_priv *priv = sd->priv;
    int a = 0;
    int b = priv->num_seen_packets;
    while (a < b) {
        int mid = a + (b - a) / 2;
        int64_t val = priv->seen_packets[mid];
        if (pos == val)
            return true;
        if (pos > val) {
            a = mid + 1;
        } else {
            b = mid;
        }
    }
    MP_TARRAY_INSERT_AT(priv, priv->seen_packets, priv->num_seen_packets, a, pos);
    return false;
}