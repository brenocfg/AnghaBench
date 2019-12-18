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
struct table {scalar_t__ num_rows; scalar_t__ data; } ;
struct record_computersystem {int /*<<< orphan*/  username; int /*<<< orphan*/  total_physical_memory; int /*<<< orphan*/  num_processors; int /*<<< orphan*/  num_logical_processors; int /*<<< orphan*/  name; int /*<<< orphan*/  model; int /*<<< orphan*/  manufacturer; scalar_t__ domainrole; int /*<<< orphan*/  domain; int /*<<< orphan*/  description; } ;
struct expr {int dummy; } ;
typedef  enum fill_status { ____Placeholder_fill_status } fill_status ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int FILL_STATUS_FAILED ; 
 int FILL_STATUS_UNFILTERED ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  compsys_descriptionW ; 
 int /*<<< orphan*/  compsys_domainW ; 
 int /*<<< orphan*/  compsys_manufacturerW ; 
 int /*<<< orphan*/  compsys_modelW ; 
 int /*<<< orphan*/  free_row_values (struct table*,scalar_t__) ; 
 int /*<<< orphan*/  get_computername () ; 
 int /*<<< orphan*/  get_logical_processor_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_processor_count () ; 
 int /*<<< orphan*/  get_total_physical_memory () ; 
 int /*<<< orphan*/  get_username () ; 
 int /*<<< orphan*/  match_row (struct table*,scalar_t__,struct expr const*,int*) ; 
 int /*<<< orphan*/  resize_table (struct table*,int,int) ; 

__attribute__((used)) static enum fill_status fill_compsys( struct table *table, const struct expr *cond )
{
    struct record_computersystem *rec;
    enum fill_status status = FILL_STATUS_UNFILTERED;
    UINT row = 0;

    if (!resize_table( table, 1, sizeof(*rec) )) return FILL_STATUS_FAILED;

    rec = (struct record_computersystem *)table->data;
    rec->description            = compsys_descriptionW;
    rec->domain                 = compsys_domainW;
    rec->domainrole             = 0; /* standalone workstation */
    rec->manufacturer           = compsys_manufacturerW;
    rec->model                  = compsys_modelW;
    rec->name                   = get_computername();
    rec->num_logical_processors = get_logical_processor_count( NULL );
    rec->num_processors         = get_processor_count();
    rec->total_physical_memory  = get_total_physical_memory();
    rec->username               = get_username();
    if (!match_row( table, row, cond, &status )) free_row_values( table, row );
    else row++;

    TRACE("created %u rows\n", row);
    table->num_rows = row;
    return status;
}