#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int flags; } ;
typedef  TYPE_1__ TLS_GROUP_INFO ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int TLS1_3_VERSION ; 
 int TLS_GROUP_ONLY_FOR_TLS1_3 ; 
 TYPE_1__* tls1_group_id_lookup (int /*<<< orphan*/ ) ; 

int tls_valid_group(SSL *s, uint16_t group_id, int version)
{
    const TLS_GROUP_INFO *ginfo = tls1_group_id_lookup(group_id);

    if (version < TLS1_3_VERSION) {
        if ((ginfo->flags & TLS_GROUP_ONLY_FOR_TLS1_3) != 0)
            return 0;
    }
    return 1;
}