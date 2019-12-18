#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ busy; } ;
struct TYPE_8__ {int flags; TYPE_1__ init; } ;
typedef  TYPE_2__ sqlite3 ;
struct TYPE_9__ {int ncFlags; } ;
typedef  TYPE_3__ NameContext ;

/* Variables and functions */
 int NC_IsDDL ; 
 int SQLITE_DqsDDL ; 
 int SQLITE_DqsDML ; 
 scalar_t__ sqlite3WritableSchema (TYPE_2__*) ; 

__attribute__((used)) static int areDoubleQuotedStringsEnabled(sqlite3 *db, NameContext *pTopNC){
  if( db->init.busy ) return 1;  /* Always support for legacy schemas */
  if( pTopNC->ncFlags & NC_IsDDL ){
    /* Currently parsing a DDL statement */
    if( sqlite3WritableSchema(db) && (db->flags & SQLITE_DqsDML)!=0 ){
      return 1;
    }
    return (db->flags & SQLITE_DqsDDL)!=0;
  }else{
    /* Currently parsing a DML statement */
    return (db->flags & SQLITE_DqsDML)!=0;
  }
}