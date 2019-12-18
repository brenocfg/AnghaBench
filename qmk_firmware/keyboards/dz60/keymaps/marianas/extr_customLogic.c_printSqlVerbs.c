#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEND_STRING (char*) ; 
#define  S_ALTER 136 
#define  S_ASTRK 135 
#define  S_DSNCT 134 
#define  S_FROM 133 
#define  S_INRJN 132 
#define  S_LFTJN 131 
#define  S_ORDER 130 
#define  S_SLCT 129 
#define  S_WHERE 128 
 int /*<<< orphan*/  activateRelativity () ; 

bool printSqlVerbs(uint16_t keycode, keyrecord_t *record)
{
  if (record->event.pressed)
  {
    switch (keycode)
    {
      case S_LFTJN: 
        SEND_STRING("LEFT JOIN"); 
        activateRelativity();
        return false;
      case S_INRJN: 
        SEND_STRING("INNER JOIN "); 
        activateRelativity();
        return false;
      case S_SLCT:  
        SEND_STRING("SELECT "); return 
        false;
      case S_FROM:  
        SEND_STRING("FROM "); return 
        false;
      case S_DSNCT: 
        SEND_STRING("DISTINCT "); return 
        false;
      case S_ORDER: 
        SEND_STRING("ORDER BY "); return 
        false;
      case S_WHERE: 
        SEND_STRING("WHERE "); return 
        false;
      case S_ALTER: 
        SEND_STRING("ALTER SESSION SET CURRENT_SCHEMA = SUPPLY;"); return false;
      case S_ASTRK: 
        SEND_STRING("* "); return false;
        
    }
  }
  return true;
}