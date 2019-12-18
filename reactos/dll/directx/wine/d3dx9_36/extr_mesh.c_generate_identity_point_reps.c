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
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static DWORD *generate_identity_point_reps(DWORD num_vertices)
{
        DWORD *id_point_reps;
        DWORD i;

        id_point_reps = HeapAlloc(GetProcessHeap(), 0, num_vertices * sizeof(*id_point_reps));
        if (!id_point_reps)
            return NULL;

        for (i = 0; i < num_vertices; i++)
        {
            id_point_reps[i] = i;
        }

        return id_point_reps;
}