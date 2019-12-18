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

/* Variables and functions */
#define  SEND_CHIKA 136 
#define  SEND_DIA 135 
#define  SEND_KANAN 134 
#define  SEND_MARI 133 
#define  SEND_RIKO 132 
#define  SEND_RUBY 131 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
#define  SEND_YOHANE 130 
#define  SEND_YOU 129 
#define  SEND_ZURA 128 
 int long_tap_timer ; 

void check_tap_and_send_key(int MEMBER) {
  if (long_tap_timer < 500) {
    switch (MEMBER) {
      case SEND_DIA:
        SEND_STRING("KUROSAWA DIA");
      break;
      case SEND_YOU:
        SEND_STRING("WATANABE YOU");
      break;
      case SEND_CHIKA:
        SEND_STRING("TAKAMI CHIKA");
      break;
      case SEND_ZURA:
        SEND_STRING("KUNIKIDA HANAMARU");
      break;
      case SEND_RUBY:
        SEND_STRING("KUROSAWA RUBY");
      break;
      case SEND_YOHANE:
        SEND_STRING("TSUSHIMA YOSHIKO");
      break;
      case SEND_RIKO:
        SEND_STRING("SAKURAUCHI RIKO");
      break;
      case SEND_MARI:
        SEND_STRING("OHARA MARI");
      break;
      case SEND_KANAN:
        SEND_STRING("MATSUURA KANAN");
      break;
      }
  }
  long_tap_timer = 0;
}