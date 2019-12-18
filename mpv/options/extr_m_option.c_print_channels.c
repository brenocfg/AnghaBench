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
struct m_channels {scalar_t__ num_chmaps; int /*<<< orphan*/ * chmaps; scalar_t__ auto_safe; int /*<<< orphan*/  set; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 char* mp_chmap_to_str (int /*<<< orphan*/ *) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 
 char* talloc_strdup_append (char*,char*) ; 

__attribute__((used)) static char *print_channels(const m_option_t *opt, const void *val)
{
    const struct m_channels *ch = val;
    if (!ch->set)
        return talloc_strdup(NULL, "");
    if (ch->auto_safe)
        return talloc_strdup(NULL, "auto-safe");
    if (ch->num_chmaps > 0) {
        char *res = talloc_strdup(NULL, "");
        for (int n = 0; n < ch->num_chmaps; n++) {
            if (n > 0)
                res = talloc_strdup_append(res, ",");
            res = talloc_strdup_append(res, mp_chmap_to_str(&ch->chmaps[n]));
        }
        return res;
    }
    return talloc_strdup(NULL, "auto");
}