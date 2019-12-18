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
struct TYPE_5__ {int /*<<< orphan*/  sid; scalar_t__ apply_trans_sid; } ;
typedef  TYPE_1__ php_session_rfc1867_progress ;
struct TYPE_6__ {int /*<<< orphan*/  (* treat_data ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_COOKIE ; 
 int /*<<< orphan*/  PARSE_GET ; 
 scalar_t__ PS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACK_VARS_COOKIE ; 
 int /*<<< orphan*/  TRACK_VARS_GET ; 
 scalar_t__ early_find_sid_in (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ sapi_module ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_cookies ; 
 int /*<<< orphan*/  use_only_cookies ; 

__attribute__((used)) static void php_session_rfc1867_early_find_sid(php_session_rfc1867_progress *progress) /* {{{ */
{

	if (PS(use_cookies)) {
		sapi_module.treat_data(PARSE_COOKIE, NULL, NULL);
		if (early_find_sid_in(&progress->sid, TRACK_VARS_COOKIE, progress)) {
			progress->apply_trans_sid = 0;
			return;
		}
	}
	if (PS(use_only_cookies)) {
		return;
	}
	sapi_module.treat_data(PARSE_GET, NULL, NULL);
	early_find_sid_in(&progress->sid, TRACK_VARS_GET, progress);
}