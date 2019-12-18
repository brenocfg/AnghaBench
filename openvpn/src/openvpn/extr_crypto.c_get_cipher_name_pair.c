#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lib_name; int /*<<< orphan*/  openvpn_name; } ;
typedef  TYPE_1__ cipher_name_pair ;

/* Variables and functions */
 TYPE_1__* cipher_name_translation_table ; 
 size_t cipher_name_translation_table_count ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const cipher_name_pair *
get_cipher_name_pair(const char *cipher_name)
{
    const cipher_name_pair *pair;
    size_t i = 0;

    /* Search for a cipher name translation */
    for (; i < cipher_name_translation_table_count; i++)
    {
        pair = &cipher_name_translation_table[i];
        if (0 == strcmp(cipher_name, pair->openvpn_name)
            || 0 == strcmp(cipher_name, pair->lib_name))
        {
            return pair;
        }
    }

    /* Nothing found, return null */
    return NULL;
}