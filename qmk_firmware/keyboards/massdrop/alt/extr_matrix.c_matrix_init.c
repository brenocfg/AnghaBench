#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  matrix_row_t ;
struct TYPE_14__ {TYPE_6__* Group; } ;
struct TYPE_12__ {int reg; } ;
struct TYPE_11__ {int reg; } ;
struct TYPE_8__ {int reg; } ;
struct TYPE_13__ {TYPE_5__ OUTCLR; TYPE_4__ DIRSET; TYPE_3__* PINCFG; TYPE_1__ DIRCLR; } ;
struct TYPE_9__ {int INEN; int PULLEN; } ;
struct TYPE_10__ {TYPE_2__ bit; } ;

/* Variables and functions */
 int MATRIX_COLS ; 
 int MATRIX_ROWS ; 
 size_t PA ; 
 size_t PB ; 
 TYPE_7__* PORT ; 
 int* col_pins ; 
 size_t* col_ports ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 int /*<<< orphan*/  mdebounced ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlast ; 
 int /*<<< orphan*/  mlatest ; 
 int* row_masks ; 
 int* row_pins ; 
 size_t* row_ports ; 

void matrix_init(void)
{
    memset(mlatest, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(mlast, 0, MATRIX_ROWS * sizeof(matrix_row_t));
    memset(mdebounced, 0, MATRIX_ROWS * sizeof(matrix_row_t));

    row_masks[PA] = 0;
    row_masks[PB] = 0;

    uint8_t row;
    for (row = 0; row < MATRIX_ROWS; row++)
    {
        PORT->Group[row_ports[row]].DIRCLR.reg = 1 << row_pins[row]; //Input
        PORT->Group[row_ports[row]].OUTCLR.reg = 1 << row_pins[row]; //Low
        PORT->Group[row_ports[row]].PINCFG[row_pins[row]].bit.INEN = 1; //Input Enable,
        PORT->Group[row_ports[row]].PINCFG[row_pins[row]].bit.PULLEN = 1; //Pull Enable
        row_masks[row_ports[row]] |= 1 << row_pins[row]; //Add pin to proper row mask
    }

    uint8_t col;
    for (col = 0; col < MATRIX_COLS; col++)
    {
        PORT->Group[col_ports[col]].DIRSET.reg = 1 << col_pins[col]; //Output
        PORT->Group[col_ports[col]].OUTCLR.reg = 1 << col_pins[col]; //Low
    }

    matrix_init_quantum();
}