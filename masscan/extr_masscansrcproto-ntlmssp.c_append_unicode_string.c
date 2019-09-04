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
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_LEN ; 
 int /*<<< orphan*/  PROTO_SMB ; 
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  banout_append_char (struct BannerOutput*,unsigned int,char) ; 
 int /*<<< orphan*/  banout_append_unicode (struct BannerOutput*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
append_unicode_string(struct BannerOutput *banout, unsigned proto, const char *name, const unsigned char *value, size_t value_length)
{
    unsigned j;
    banout_append_char(banout, proto, ' ');
    banout_append(banout, PROTO_SMB, name, AUTO_LEN);
    banout_append_char(banout, proto, '=');
    for (j=0; j<value_length; j += 2) {
        unsigned c = value[j] | value[j+1]<<8;
        banout_append_unicode(banout, PROTO_SMB, c);
    }
}