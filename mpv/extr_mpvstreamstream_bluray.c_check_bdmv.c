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
struct TYPE_3__ {char* member_0; int member_1; } ;
typedef  TYPE_1__ bstr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ bstr_startswith0 (TYPE_1__,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_basename (char const*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool check_bdmv(const char *path)
{
    if (strcasecmp(mp_basename(path), "MovieObject.bdmv"))
        return false;

    FILE *temp = fopen(path, "rb");
    if (!temp)
        return false;

    char data[50] = {0};

    fread(data, 50, 1, temp);
    fclose(temp);

    bstr bdata = {data, 50};

    return bstr_startswith0(bdata, "MOBJ0100") || // AVCHD
           bstr_startswith0(bdata, "MOBJ0200") || // Blu-ray
           bstr_startswith0(bdata, "MOBJ0300");   // UHD BD
}