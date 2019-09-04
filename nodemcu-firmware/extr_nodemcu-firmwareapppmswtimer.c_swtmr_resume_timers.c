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
typedef  scalar_t__ uint32 ;
struct TYPE_4__ {scalar_t__ volatile timer_expire; struct TYPE_4__* timer_next; } ;
typedef  TYPE_1__ os_timer_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  FRC2_COUNT_ADDRESS ; 
 int L_REGISTRY ; 
 scalar_t__ RTC_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUSP_LIST_STR ; 
 int /*<<< orphan*/ * lua_getstate () ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  push_swtmr_registry_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* timer_list ; 

void swtmr_resume_timers(){
  lua_State* L = lua_getstate();

  //get swtimer table
  push_swtmr_registry_key(L);
  lua_rawget(L, L_REGISTRY);

  //get suspended_timer_list lightuserdata
  lua_pushstring(L, SUSP_LIST_STR);
  lua_rawget(L, -2);

  //check for existence of swtimer table and the suspended_timer_list pointer userdata, return if not found
  if(!lua_istable(L, -2) || !lua_isuserdata(L, -1)){
    // not necessarily an error maybe there are legitimately no timers to resume
    lua_pop(L, 2);
    return;
  }

  os_timer_t* suspended_timer_list_ptr = lua_touserdata(L, -1);
  lua_pop(L, 1); //pop suspended timer list userdata from stack

  //since timers will be resumed, the suspended_timer_list lightuserdata can be cleared from swtimer table
  lua_pushstring(L, SUSP_LIST_STR);
  lua_pushnil(L);
  lua_rawset(L, -3);


  lua_pop(L, 1); //pop swtimer table from stack

  volatile uint32 frc2_count = RTC_REG_READ(FRC2_COUNT_ADDRESS);

  //this section does the actual resuming of the suspended timer(s)
  while(suspended_timer_list_ptr != NULL){
    os_timer_t* timer_list_ptr = timer_list;

    //the pointer to next suspended timer must be saved, the current suspended timer will be removed from the list
    os_timer_t* next_suspended_timer_ptr = suspended_timer_list_ptr->timer_next;

    suspended_timer_list_ptr->timer_expire += frc2_count;

    //traverse timer_list to determine where to insert suspended timer
    while(timer_list_ptr != NULL){
      if(suspended_timer_list_ptr->timer_expire > timer_list_ptr->timer_expire){
        if(timer_list_ptr->timer_next != NULL){
          //current timer is not at tail of timer_list
          if(suspended_timer_list_ptr->timer_expire < timer_list_ptr->timer_next->timer_expire){
            //insert suspended timer between current timer and next timer
            suspended_timer_list_ptr->timer_next = timer_list_ptr->timer_next;
            timer_list_ptr->timer_next = suspended_timer_list_ptr;
            break; //timer resumed exit while loop
          }
          else{
            //suspended timer expire is larger than next timer
          }
        }
        else{
          //current timer is at tail of timer_list and suspended timer expire is greater then current timer
          //append timer to end of timer_list
          timer_list_ptr->timer_next = suspended_timer_list_ptr;
          suspended_timer_list_ptr->timer_next = NULL;
          break; //timer resumed exit while loop
        }
      }
      else if(timer_list_ptr == timer_list){
        //insert timer at head of list
        suspended_timer_list_ptr->timer_next = timer_list_ptr;
        timer_list = timer_list_ptr = suspended_timer_list_ptr;
        break; //timer resumed exit while loop
      }
      //suspended timer expire is larger than next timer
      //timer not resumed, next timer in timer_list
      timer_list_ptr = timer_list_ptr->timer_next;
    }
    //timer was resumed, next suspended timer
    suspended_timer_list_ptr = next_suspended_timer_ptr;
  }
  return;
}