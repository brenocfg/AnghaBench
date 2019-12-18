#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* data; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ PKEY_DATA ;
typedef  TYPE_2__ EVP_TEST ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_derive_set_peer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ find_key (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int parse_bin (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pkey_test_ctrl (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  public_keys ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int pderive_test_parse(EVP_TEST *t,
                              const char *keyword, const char *value)
{
    PKEY_DATA *kdata = t->data;

    if (strcmp(keyword, "PeerKey") == 0) {
        EVP_PKEY *peer;
        if (find_key(&peer, value, public_keys) == 0)
            return -1;
        if (EVP_PKEY_derive_set_peer(kdata->ctx, peer) <= 0)
            return -1;
        return 1;
    }
    if (strcmp(keyword, "SharedSecret") == 0)
        return parse_bin(value, &kdata->output, &kdata->output_len);
    if (strcmp(keyword, "Ctrl") == 0)
        return pkey_test_ctrl(t, kdata->ctx, value);
    return 0;
}