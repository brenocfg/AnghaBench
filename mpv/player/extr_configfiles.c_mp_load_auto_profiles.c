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
struct MPContext {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_auto_load_profile (struct MPContext*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_load_per_file_config (struct MPContext*) ; 
 int /*<<< orphan*/  mp_split_proto (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_splitext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mp_load_auto_profiles(struct MPContext *mpctx)
{
    mp_auto_load_profile(mpctx, "protocol",
                         mp_split_proto(bstr0(mpctx->filename), NULL));
    mp_auto_load_profile(mpctx, "extension",
                         bstr0(mp_splitext(mpctx->filename, NULL)));

    mp_load_per_file_config(mpctx);
}