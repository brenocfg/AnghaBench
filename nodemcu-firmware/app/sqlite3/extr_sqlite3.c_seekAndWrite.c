#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lastErrno; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int seekAndWriteFd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int seekAndWrite(unixFile *id, i64 offset, const void *pBuf, int cnt){
  return seekAndWriteFd(id->h, offset, pBuf, cnt, &id->lastErrno);
}