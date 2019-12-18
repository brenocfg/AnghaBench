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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  ac ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3Get4byte (unsigned char*) ; 
 int sqlite3OsRead (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read32bits(sqlite3_file *fd, i64 offset, u32 *pRes){
  unsigned char ac[4];
  int rc = sqlite3OsRead(fd, ac, sizeof(ac), offset);
  if( rc==SQLITE_OK ){
    *pRes = sqlite3Get4byte(ac);
  }
  return rc;
}