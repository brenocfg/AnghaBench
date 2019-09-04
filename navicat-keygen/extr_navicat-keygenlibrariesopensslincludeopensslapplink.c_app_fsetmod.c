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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _O_TEXT ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ *) ; 
 int _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int app_fsetmod(FILE *fp, char mod)
{
    return _setmode(_fileno(fp), mod == 'b' ? _O_BINARY : _O_TEXT);
}