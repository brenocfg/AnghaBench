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
struct TYPE_3__ {scalar_t__ hash; int /*<<< orphan*/  hash_idx; } ;
typedef  TYPE_1__ SIGALG_LOOKUP ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 scalar_t__ NID_undef ; 
 int /*<<< orphan*/ * ssl_md (int /*<<< orphan*/ ) ; 

int tls1_lookup_md(const SIGALG_LOOKUP *lu, const EVP_MD **pmd)
{
    const EVP_MD *md;
    if (lu == NULL)
        return 0;
    /* lu->hash == NID_undef means no associated digest */
    if (lu->hash == NID_undef) {
        md = NULL;
    } else {
        md = ssl_md(lu->hash_idx);
        if (md == NULL)
            return 0;
    }
    if (pmd)
        *pmd = md;
    return 1;
}