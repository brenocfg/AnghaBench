#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int npyiter_opitflags ;
typedef  int npy_uint32 ;
typedef  scalar_t__ npy_intp ;
struct TYPE_25__ {scalar_t__ elsize; } ;
typedef  int /*<<< orphan*/  PyTypeObject ;
typedef  TYPE_1__ PyArray_Descr ;
typedef  TYPE_1__ PyArrayObject ;
typedef  int /*<<< orphan*/  NpyIter_BufferData ;
typedef  int /*<<< orphan*/  NpyIter_AxisData ;
typedef  int /*<<< orphan*/  NpyIter ;

/* Variables and functions */
 scalar_t__ IsUintAligned (TYPE_1__*) ; 
 scalar_t__ NAD_SHAPE (int /*<<< orphan*/ *) ; 
 void** NAD_STRIDES (int /*<<< orphan*/ *) ; 
 void** NBF_STRIDES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NIT_ADVANCE_AXISDATA (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * NIT_AXISDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ NIT_AXISDATA_SIZEOF (int,int,int) ; 
 int /*<<< orphan*/ * NIT_BUFFERDATA (int /*<<< orphan*/ *) ; 
 int NIT_ITFLAGS (int /*<<< orphan*/ *) ; 
 int NIT_NDIM (int /*<<< orphan*/ *) ; 
 int NIT_NOP (int /*<<< orphan*/ *) ; 
 TYPE_1__** NIT_OPERANDS (int /*<<< orphan*/ *) ; 
 int const NPY_ITER_CONTIG ; 
 int const NPY_ITER_COPY ; 
 int NPY_ITER_COPY_IF_OVERLAP ; 
 int const NPY_ITER_NO_SUBTYPE ; 
 int const NPY_ITER_OVERLAP_ASSUME_ELEMENTWISE ; 
 int const NPY_ITER_UPDATEIFCOPY ; 
 int NPY_ITFLAG_BUFFER ; 
 int /*<<< orphan*/  NPY_IT_DBG_PRINT (char*) ; 
 int NPY_OP_ITFLAG_ALIGNED ; 
 int NPY_OP_ITFLAG_BUFNEVER ; 
 int NPY_OP_ITFLAG_CAST ; 
 int NPY_OP_ITFLAG_FORCECOPY ; 
 int NPY_OP_ITFLAG_HAS_WRITEBACK ; 
 int NPY_OP_ITFLAG_READ ; 
 int NPY_OP_ITFLAG_REDUCE ; 
 int NPY_OP_ITFLAG_WRITE ; 
 int NPY_OP_ITFLAG_WRITEMASKED ; 
 scalar_t__ PyArray_BYTES (TYPE_1__*) ; 
 scalar_t__ PyArray_CompareLists (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ PyArray_CopyInto (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PyArray_DATA (TYPE_1__*) ; 
 scalar_t__ PyArray_DESCR (TYPE_1__*) ; 
 int /*<<< orphan*/ * PyArray_DIMS (TYPE_1__*) ; 
 scalar_t__ PyArray_NDIM (TYPE_1__*) ; 
 scalar_t__ PyArray_NewFromDescr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyArray_STRIDES (TYPE_1__*) ; 
 scalar_t__ PyArray_SetWritebackIfCopyBase (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PyArray_Type ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_TypeError ; 
 int /*<<< orphan*/  Py_DECREF (TYPE_1__*) ; 
 int /*<<< orphan*/  Py_INCREF (TYPE_1__*) ; 
 int /*<<< orphan*/  check_mask_for_writemasked_reduction (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* npyiter_new_temp_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int,int /*<<< orphan*/ *,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  npyiter_replace_axisdata (int /*<<< orphan*/ *,int,TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ solve_may_have_internal_overlap (TYPE_1__*,int) ; 
 int solve_may_share_memory (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static int
npyiter_allocate_arrays(NpyIter *iter,
                        npy_uint32 flags,
                        PyArray_Descr **op_dtype, PyTypeObject *subtype,
                        const npy_uint32 *op_flags, npyiter_opitflags *op_itflags,
                        int **op_axes)
{
    npy_uint32 itflags = NIT_ITFLAGS(iter);
    int idim, ndim = NIT_NDIM(iter);
    int iop, nop = NIT_NOP(iter);

    int check_writemasked_reductions = 0;

    NpyIter_BufferData *bufferdata = NULL;
    PyArrayObject **op = NIT_OPERANDS(iter);

    if (itflags & NPY_ITFLAG_BUFFER) {
        bufferdata = NIT_BUFFERDATA(iter);
    }

    if (flags & NPY_ITER_COPY_IF_OVERLAP) {
        /*
         * Perform operand memory overlap checks, if requested.
         *
         * If any write operand has memory overlap with any read operand,
         * eliminate all overlap by making temporary copies, by enabling
         * NPY_OP_ITFLAG_FORCECOPY for the write operand to force WRITEBACKIFCOPY.
         *
         * Operands with NPY_ITER_OVERLAP_ASSUME_ELEMENTWISE enabled are not
         * considered overlapping if the arrays are exactly the same. In this
         * case, the iterator loops through them in the same order element by
         * element.  (As usual, the user-provided inner loop is assumed to be
         * able to deal with this level of simple aliasing.)
         */
        for (iop = 0; iop < nop; ++iop) {
            int may_share_memory = 0;
            int iother;

            if (op[iop] == NULL) {
                /* Iterator will always allocate */
                continue;
            }

            if (!(op_itflags[iop] & NPY_OP_ITFLAG_WRITE)) {
                /*
                 * Copy output operands only, not inputs.
                 * A more sophisticated heuristic could be
                 * substituted here later.
                 */
                continue;
            }

            for (iother = 0; iother < nop; ++iother) {
                if (iother == iop || op[iother] == NULL) {
                    continue;
                }

                if (!(op_itflags[iother] & NPY_OP_ITFLAG_READ)) {
                    /* No data dependence for arrays not read from */
                    continue;
                }

                if (op_itflags[iother] & NPY_OP_ITFLAG_FORCECOPY) {
                    /* Already copied */
                    continue;
                }

                /*
                 * If the arrays are views to exactly the same data, no need
                 * to make copies, if the caller (eg ufunc) says it accesses
                 * data only in the iterator order.
                 *
                 * However, if there is internal overlap (e.g. a zero stride on
                 * a non-unit dimension), a copy cannot be avoided.
                 */
                if ((op_flags[iop] & NPY_ITER_OVERLAP_ASSUME_ELEMENTWISE) &&
                    (op_flags[iother] & NPY_ITER_OVERLAP_ASSUME_ELEMENTWISE) &&
                    PyArray_BYTES(op[iop]) == PyArray_BYTES(op[iother]) &&
                    PyArray_NDIM(op[iop]) == PyArray_NDIM(op[iother]) &&
                    PyArray_CompareLists(PyArray_DIMS(op[iop]),
                                         PyArray_DIMS(op[iother]),
                                         PyArray_NDIM(op[iop])) &&
                    PyArray_CompareLists(PyArray_STRIDES(op[iop]),
                                         PyArray_STRIDES(op[iother]),
                                         PyArray_NDIM(op[iop])) &&
                    PyArray_DESCR(op[iop]) == PyArray_DESCR(op[iother]) &&
                    solve_may_have_internal_overlap(op[iop], 1) == 0) {

                    continue;
                }

                /*
                 * Use max work = 1. If the arrays are large, it might
                 * make sense to go further.
                 */
                may_share_memory = solve_may_share_memory(op[iop],
                                                          op[iother],
                                                          1);

                if (may_share_memory) {
                    op_itflags[iop] |= NPY_OP_ITFLAG_FORCECOPY;
                    break;
                }
            }
        }
    }

    for (iop = 0; iop < nop; ++iop) {
        /*
         * Check whether there are any WRITEMASKED REDUCE operands
         * which should be validated after all the strides are filled
         * in.
         */
        if ((op_itflags[iop] &
                (NPY_OP_ITFLAG_WRITEMASKED | NPY_OP_ITFLAG_REDUCE)) ==
                        (NPY_OP_ITFLAG_WRITEMASKED | NPY_OP_ITFLAG_REDUCE)) {
            check_writemasked_reductions = 1;
        }

        /* NULL means an output the iterator should allocate */
        if (op[iop] == NULL) {
            PyArrayObject *out;
            PyTypeObject *op_subtype;
            int ondim = ndim;

            /* Check whether the subtype was disabled */
            op_subtype = (op_flags[iop] & NPY_ITER_NO_SUBTYPE) ?
                                                &PyArray_Type : subtype;

            /* Allocate the output array */
            out = npyiter_new_temp_array(iter, op_subtype,
                                        flags, &op_itflags[iop],
                                        ondim,
                                        NULL,
                                        op_dtype[iop],
                                        op_axes ? op_axes[iop] : NULL);
            if (out == NULL) {
                return 0;
            }

            op[iop] = out;

            /*
             * Now we need to replace the pointers and strides with values
             * from the new array.
             */
            npyiter_replace_axisdata(iter, iop, op[iop], ondim,
                    PyArray_DATA(op[iop]), op_axes ? op_axes[iop] : NULL);

            /*
             * New arrays are guaranteed true-aligned, but copy/cast code
             * needs uint-alignment in addition.
             */
            if (IsUintAligned(out)) {
                op_itflags[iop] |= NPY_OP_ITFLAG_ALIGNED;
            }
            /* New arrays need no cast */
            op_itflags[iop] &= ~NPY_OP_ITFLAG_CAST;
        }
        /*
         * If casting is required, the operand is read-only, and
         * it's an array scalar, make a copy whether or not the
         * copy flag is enabled.
         */
        else if ((op_itflags[iop] & (NPY_OP_ITFLAG_CAST |
                         NPY_OP_ITFLAG_READ |
                         NPY_OP_ITFLAG_WRITE)) == (NPY_OP_ITFLAG_CAST |
                                                   NPY_OP_ITFLAG_READ) &&
                          PyArray_NDIM(op[iop]) == 0) {
            PyArrayObject *temp;
            Py_INCREF(op_dtype[iop]);
            temp = (PyArrayObject *)PyArray_NewFromDescr(
                                        &PyArray_Type, op_dtype[iop],
                                        0, NULL, NULL, NULL, 0, NULL);
            if (temp == NULL) {
                return 0;
            }
            if (PyArray_CopyInto(temp, op[iop]) != 0) {
                Py_DECREF(temp);
                return 0;
            }
            Py_DECREF(op[iop]);
            op[iop] = temp;

            /*
             * Now we need to replace the pointers and strides with values
             * from the temporary array.
             */
            npyiter_replace_axisdata(iter, iop, op[iop], 0,
                    PyArray_DATA(op[iop]), NULL);

            /*
             * New arrays are guaranteed true-aligned, but copy/cast code
             * needs uint-alignment in addition.
             */
            if (IsUintAligned(temp)) {
                op_itflags[iop] |= NPY_OP_ITFLAG_ALIGNED;
            }
            /*
             * New arrays need no cast, and in the case
             * of scalars, always have stride 0 so never need buffering
             */
            op_itflags[iop] |= NPY_OP_ITFLAG_BUFNEVER;
            op_itflags[iop] &= ~NPY_OP_ITFLAG_CAST;
            if (itflags & NPY_ITFLAG_BUFFER) {
                NBF_STRIDES(bufferdata)[iop] = 0;
            }
        }
        /*
         * Make a temporary copy if,
         * 1. If casting is required and permitted, or,
         * 2. If force-copy is requested
         */
        else if (((op_itflags[iop] & NPY_OP_ITFLAG_CAST) &&
                        (op_flags[iop] &
                        (NPY_ITER_COPY|NPY_ITER_UPDATEIFCOPY))) ||
                 (op_itflags[iop] & NPY_OP_ITFLAG_FORCECOPY)) {
            PyArrayObject *temp;
            int ondim = PyArray_NDIM(op[iop]);

            /* Allocate the temporary array, if possible */
            temp = npyiter_new_temp_array(iter, &PyArray_Type,
                                        flags, &op_itflags[iop],
                                        ondim,
                                        PyArray_DIMS(op[iop]),
                                        op_dtype[iop],
                                        op_axes ? op_axes[iop] : NULL);
            if (temp == NULL) {
                return 0;
            }

            /*
             * If the data will be read, copy it into temp.
             * TODO: It might be possible to do a view into
             *       op[iop]'s mask instead here.
             */
            if (op_itflags[iop] & NPY_OP_ITFLAG_READ) {
                if (PyArray_CopyInto(temp, op[iop]) != 0) {
                    Py_DECREF(temp);
                    return 0;
                }
            }
            /* If the data will be written to, set WRITEBACKIFCOPY
               and require a context manager */
            if (op_itflags[iop] & NPY_OP_ITFLAG_WRITE) {
                Py_INCREF(op[iop]);
                if (PyArray_SetWritebackIfCopyBase(temp, op[iop]) < 0) {
                    Py_DECREF(temp);
                    return 0;
                }
                op_itflags[iop] |= NPY_OP_ITFLAG_HAS_WRITEBACK;
            }

            Py_DECREF(op[iop]);
            op[iop] = temp;

            /*
             * Now we need to replace the pointers and strides with values
             * from the temporary array.
             */
            npyiter_replace_axisdata(iter, iop, op[iop], ondim,
                    PyArray_DATA(op[iop]), op_axes ? op_axes[iop] : NULL);

            /*
             * New arrays are guaranteed true-aligned, but copy/cast code
             * additionally needs uint-alignment in addition.
             */
            if (IsUintAligned(temp)) {
                op_itflags[iop] |= NPY_OP_ITFLAG_ALIGNED;
            }
            /* The temporary copy needs no cast */
            op_itflags[iop] &= ~NPY_OP_ITFLAG_CAST;
        }
        else {
            /*
             * Buffering must be enabled for casting/conversion if copy
             * wasn't specified.
             */
            if ((op_itflags[iop] & NPY_OP_ITFLAG_CAST) &&
                                  !(itflags & NPY_ITFLAG_BUFFER)) {
                PyErr_SetString(PyExc_TypeError,
                        "Iterator operand required copying or buffering, "
                        "but neither copying nor buffering was enabled");
                return 0;
            }

            /*
             * If the operand is aligned, any buffering can use aligned
             * optimizations.
             */
            if (IsUintAligned(op[iop])) {
                op_itflags[iop] |= NPY_OP_ITFLAG_ALIGNED;
            }
        }

        /* Here we can finally check for contiguous iteration */
        if (op_flags[iop] & NPY_ITER_CONTIG) {
            NpyIter_AxisData *axisdata = NIT_AXISDATA(iter);
            npy_intp stride = NAD_STRIDES(axisdata)[iop];

            if (stride != op_dtype[iop]->elsize) {
                NPY_IT_DBG_PRINT("Iterator: Setting NPY_OP_ITFLAG_CAST "
                                    "because of NPY_ITER_CONTIG\n");
                op_itflags[iop] |= NPY_OP_ITFLAG_CAST;
                if (!(itflags & NPY_ITFLAG_BUFFER)) {
                    PyErr_SetString(PyExc_TypeError,
                            "Iterator operand required buffering, "
                            "to be contiguous as requested, but "
                            "buffering is not enabled");
                    return 0;
                }
            }
        }

        /*
         * If no alignment, byte swap, or casting is needed,
         * the inner stride of this operand works for the whole
         * array, we can set NPY_OP_ITFLAG_BUFNEVER.
         */
        if ((itflags & NPY_ITFLAG_BUFFER) &&
                                !(op_itflags[iop] & NPY_OP_ITFLAG_CAST)) {
            NpyIter_AxisData *axisdata = NIT_AXISDATA(iter);
            if (ndim <= 1) {
                op_itflags[iop] |= NPY_OP_ITFLAG_BUFNEVER;
                NBF_STRIDES(bufferdata)[iop] = NAD_STRIDES(axisdata)[iop];
            }
            else if (PyArray_NDIM(op[iop]) > 0) {
                npy_intp stride, shape, innerstride = 0, innershape;
                npy_intp sizeof_axisdata =
                                    NIT_AXISDATA_SIZEOF(itflags, ndim, nop);
                /* Find stride of the first non-empty shape */
                for (idim = 0; idim < ndim; ++idim) {
                    innershape = NAD_SHAPE(axisdata);
                    if (innershape != 1) {
                        innerstride = NAD_STRIDES(axisdata)[iop];
                        break;
                    }
                    NIT_ADVANCE_AXISDATA(axisdata, 1);
                }
                ++idim;
                NIT_ADVANCE_AXISDATA(axisdata, 1);
                /* Check that everything could have coalesced together */
                for (; idim < ndim; ++idim) {
                    stride = NAD_STRIDES(axisdata)[iop];
                    shape = NAD_SHAPE(axisdata);
                    if (shape != 1) {
                        /*
                         * If N times the inner stride doesn't equal this
                         * stride, the multi-dimensionality is needed.
                         */
                        if (innerstride*innershape != stride) {
                            break;
                        }
                        else {
                            innershape *= shape;
                        }
                    }
                    NIT_ADVANCE_AXISDATA(axisdata, 1);
                }
                /*
                 * If we looped all the way to the end, one stride works.
                 * Set that stride, because it may not belong to the first
                 * dimension.
                 */
                if (idim == ndim) {
                    op_itflags[iop] |= NPY_OP_ITFLAG_BUFNEVER;
                    NBF_STRIDES(bufferdata)[iop] = innerstride;
                }
            }
        }
    }

    if (check_writemasked_reductions) {
        for (iop = 0; iop < nop; ++iop) {
            /*
             * Check whether there are any WRITEMASKED REDUCE operands
             * which should be validated now that all the strides are filled
             * in.
             */
            if ((op_itflags[iop] &
                    (NPY_OP_ITFLAG_WRITEMASKED | NPY_OP_ITFLAG_REDUCE)) ==
                        (NPY_OP_ITFLAG_WRITEMASKED | NPY_OP_ITFLAG_REDUCE)) {
                /*
                 * If the ARRAYMASK has 'bigger' dimensions
                 * than this REDUCE WRITEMASKED operand,
                 * the result would be more than one mask
                 * value per reduction element, something which
                 * is invalid. This function provides validation
                 * for that.
                 */
                if (!check_mask_for_writemasked_reduction(iter, iop)) {
                    return 0;
                }
            }
        }
    }

    return 1;
}