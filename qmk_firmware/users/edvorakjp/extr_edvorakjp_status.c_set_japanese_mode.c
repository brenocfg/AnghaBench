#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ enable_kc_lang; } ;
struct TYPE_3__ {int japanese_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SS_LALT (char*) ; 
 int /*<<< orphan*/  SS_TAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X_LANG1 ; 
 int /*<<< orphan*/  X_LANG2 ; 
 TYPE_2__ edvorakjp_config ; 
 TYPE_1__ edvorakjp_state ; 

void set_japanese_mode(bool new_state) {
  edvorakjp_state.japanese_mode = new_state;
  if (edvorakjp_state.japanese_mode) {
    if (edvorakjp_config.enable_kc_lang) {
      SEND_STRING(SS_TAP(X_LANG1));
    } else {
      SEND_STRING(SS_LALT("`"));
    }
  } else {
    if (edvorakjp_config.enable_kc_lang) {
      SEND_STRING(SS_TAP(X_LANG2));
    } else {
      SEND_STRING(SS_LALT("`"));
    }
  }
}